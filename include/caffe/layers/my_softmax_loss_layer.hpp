#ifndef CAFFE_MY_SOFTMAX_WITH_LOSS_LAYER_HPP_
#define CAFFE_MY_SOFTMAX_WITH_LOSS_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

#include "caffe/layers/loss_layer.hpp"
#include "caffe/layers/softmax_layer.hpp"

namespace caffe {

template <typename Dtype>
class MySoftmaxWithLossLayer : public LossLayer<Dtype> {
 public:
  explicit MySoftmaxWithLossLayer(const LayerParameter& param)
      : LossLayer<Dtype>(param) {}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  // virtual inline const char* type() const { return "MySoftmaxWithLoss"; }
  // virtual inline int ExactNumTopBlobs() const { return -1; }
  // virtual inline int MinTopBlobs() const { return 1; }
  // virtual inline int MaxTopBlobs() const { return 2; }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

  /// Read the normalization mode parameter and compute the normalizer based
  /// on the blob size.  If normalization_mode is VALID, the count of valid
  /// outputs will be read from valid_count, unless it is -1 in which case
  /// all outputs are assumed to be valid.
  // virtual Dtype get_normalizer(
  //     LossParameter_NormalizationMode normalization_mode, int valid_count);

  /// The internal SoftmaxLayer used to map predictions to a distribution.
  shared_ptr<Layer<Dtype> > softmax_layer_;
  /// prob stores the output probability predictions from the SoftmaxLayer.
  Blob<Dtype> prob_;
  /// bottom vector holder used in call to the underlying SoftmaxLayer::Forward
  vector<Blob<Dtype>*> softmax_bottom_vec_;
  /// top vector holder used in call to the underlying SoftmaxLayer::Forward
  vector<Blob<Dtype>*> softmax_top_vec_;
  // /// Whether to ignore instances with a certain label.
  // bool has_ignore_label_;
  // /// The label indicating that an instance should be ignored.
  // int ignore_label_;
  // /// How to normalize the output loss.
  // LossParameter_NormalizationMode normalization_;

  // int softmax_axis_, outer_num_, inner_num_;
  int nClassLabel;
  int nRotation;
  int nSample;
  int num;
  bool using_upright;
  vector<int> labelR; // class + rotation
  vector<int> max_ang;
  vector< vector<int> > ang;

};

}  // namespace caffe

#endif  // CAFFE_MY_SOFTMAX_WITH_LOSS_LAYER_HPP_
