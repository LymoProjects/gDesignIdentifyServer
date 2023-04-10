#pragma once

#include <string>

namespace gd__ {
    struct dnnWorkConf {
        static constexpr
        char const * faceDetOnnxPath {"./dnn/face_detection_yunet_2022mar.onnx"};
        static constexpr
        char const * faceRecOnnxPath {"./dnn/face_recognition_sface_2021dec.onnx"};
    };
}