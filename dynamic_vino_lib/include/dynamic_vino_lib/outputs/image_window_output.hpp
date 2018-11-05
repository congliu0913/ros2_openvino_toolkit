/*
 * Copyright (c) 2018 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
* @brief A header file with declaration for ImageWindowOutput Class
* @file image_window_output.h
*/

#ifndef DYNAMIC_VINO_LIB__OUTPUTS__IMAGE_WINDOW_OUTPUT_HPP_
#define DYNAMIC_VINO_LIB__OUTPUTS__IMAGE_WINDOW_OUTPUT_HPP_

#include <vector>
#include <string>
#include "dynamic_vino_lib/outputs/base_output.hpp"

namespace Outputs {
/**
 * @class ImageWindowOutput
 * @brief This class handles and shows the detection result with image window.
 */
class ImageWindowOutput : public BaseOutput {
 public:
  explicit ImageWindowOutput(const std::string& window_name,
                             int focal_length = 950);
  /**
   * @brief Calculate the camera matrix of a frame for image
   * window output.
   * @param[in] A frame.
   */
  void feedFrame(const cv::Mat&) override;
  /**
   * @brief Show all the contents generated by the accept
   * functions with image window.
   */
  void handleOutput() override;
  /**
   * @brief Generate image window output content according to
   * the face detection result.
   * @param[in] A face detection result objetc.
   */
  void accept(
      const std::vector<dynamic_vino_lib::FaceDetectionResult>&) override;
  /**
   * @brief Generate image window output content according to
   * the emotion detection result.
   * @param[in] A emotion detection result objetc.
   */
  void accept(
      const std::vector<dynamic_vino_lib::EmotionsResult>&) override;
  /**
   * @brief Generate image window output content according to
   * the age and gender detection result.
   * @param[in] A head pose detection result objetc.
   */
  void accept(
      const std::vector<dynamic_vino_lib::HeadPoseResult>&) override;
  /**
   * @brief Generate image window output content according to
   * the headpose detection result.
   * @param[in] An age gender detection result objetc.
   */
  void accept(
    const std::vector<dynamic_vino_lib::AgeGenderResult>&) override;

 private:
   void initOutputs(unsigned size);
   /**
    * @brief Calculate the axises of the coordinates for showing
    * the image window. 
    */
   cv::Point calcAxis(cv::Mat r, double cx, double cy, double cz, cv::Point cp);
   /**
    * @brief Calculte the rotation transform from the rotation pose.
    * @param[in] yaw Yaw rotation value.
    * @param[in] pitch Pitch rotation value.
    * @param[in] roll Roll rotation value.
    */
   cv::Mat getRotationTransform(double yaw, double pitch, double roll);

  struct OutputData {
    std::string desc;
    cv::Rect rect;
    cv::Scalar scalar;
    cv::Point hp_cp;   // for headpose, center point
    cv::Point hp_x;    // for headpose, end point of xAxis
    cv::Point hp_y;    // for headpose, end point of yAxis
    cv::Point hp_zs;   // for headpose, start point of zAxis
    cv::Point hp_ze;   // for headpose, end point of zAxis
  };

  std::vector<OutputData> outputs_;
  const std::string window_name_;
  float focal_length_;
  cv::Mat camera_matrix_;
};
}  // namespace Outputs
#endif  // DYNAMIC_VINO_LIB__OUTPUTS__IMAGE_WINDOW_OUTPUT_HPP_