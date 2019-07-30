/*
 * COPYRIGHT AND PERMISSION NOTICE
 * Penn Software MSCKF_VIO
 * Copyright (C) 2017 The Trustees of the University of Pennsylvania
 * All rights reserved.
 */

#ifndef LOOP_CLOSURE_NODELET_H
#define LOOP_CLOSURE_NODELET_H

#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>
#include <msckf_vio/loop_closure.h>

namespace msckf_vio {

class loop_closure;

class LoopClosureNodelet : public nodelet::Nodelet {
public:
  LoopClosureNodelet() { return; }
  ~LoopClosureNodelet() { return; }

private:
  virtual void onInit();
  LoopClosurePtr loop_closure_ptr;
};
} // end namespace msckf_vio

#endif

