/*
 * COPYRIGHT AND PERMISSION NOTICE
 * Penn Software MSCKF_VIO
 * Copyright (C) 2017 The Trustees of the University of Pennsylvania
 * All rights reserved.
 */

#include <msckf_vio/loop_closure_nodelet.h>

using namespace std;

namespace msckf_vio {
void LoopClosureNodelet::onInit() {
  ros::NodeHandle& private_nh = getPrivateNodeHandle();
  loop_closure* lc = new loop_closure(private_nh);
  cout << "Step in loop_closure_nodelet~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  exit(-1);
  loop_closure_ptr.reset(lc);
  if (!loop_closure_ptr->initialize()) {
    ROS_ERROR("Cannot initialize Image Processor...");
    return;
  }
  return;
}

PLUGINLIB_EXPORT_CLASS(msckf_vio::LoopClosureNodelet,
    nodelet::Nodelet);

} // end namespace msckf_vio

