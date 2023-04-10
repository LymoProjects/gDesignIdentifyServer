#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <exception>

#include <co/http.h>
#include <co/str.h>
#include <co/co/pool.h>

#include "opencv2/core/cvstd_wrapper.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect/face.hpp"

#include "httpHeaderConf.hpp"
#include "dnnWorkConf.hpp"
#include "matCvt.hpp"

namespace gd__ {
    struct httpServerConf {
        static
        auto httpOnReq(http::Req const & req, http::Res & res) -> void {
            res.set_status(200);

            if (!req.is_method_post()) {
                addFailedHeader(res, "wrong method.");

                return;
            }

            if (std::string_view(req.header(httpHeaderConf::kOperation)) != httpHeaderConf::kIdentify) {
                addFailedHeader(res, "wrong operation.");

                return;
            }

            if (std::string_view(req.header(httpHeaderConf::kImg)).empty()) {
                addFailedHeader(res, "empty img header.");

                return;
            }

            generateFeature(req.header(httpHeaderConf::kImg), res);
        }

        static
        auto generateFeature(std::string const & imgName, http::Res & res) -> void {
            try {
                cv::Mat imgData(cv::imread("images/" + imgName));

                cv::resize(imgData, imgData, cv::Size(200, 300));

                auto faceDtor {cv::FaceDetectorYN::create(dnnWorkConf::faceDetOnnxPath, "", imgData.size())};

                cv::Mat imgDetected;

                faceDtor->detect(imgData, imgDetected);

                auto faceRec {cv::FaceRecognizerSF::create(dnnWorkConf::faceRecOnnxPath, "")};

                cv::Mat imgAligned;

                faceRec->alignCrop(imgData, imgDetected.row(0), imgAligned);

                cv::Mat imgFeature;

                faceRec->feature(imgAligned, imgFeature);

                auto parts {str::split(imgName, '.')};

                std::string featureBinPath("features/");
                featureBinPath += parts[0].c_str();
                featureBinPath += ".bin";

                SaveMatBinary(featureBinPath, imgFeature);

                addSuccessHeader(res);
            } catch (std::exception const & e) {
                addFailedHeader(res, e.what());

                std::cerr << e.what() << '\n';
            }
        }

        static
        auto addSuccessHeader(http::Res & res) -> void {
            res.add_header(httpHeaderConf::kResult, httpHeaderConf::kSuccess);
        }

        static
        auto addFailedHeader(http::Res & res, std::string const & err) -> void {
            res.add_header(httpHeaderConf::kResult, httpHeaderConf::kFailed);
            res.add_header(httpHeaderConf::kReason, err.c_str());
        }
    };
}