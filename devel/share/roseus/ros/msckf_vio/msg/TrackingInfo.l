;; Auto-generated. Do not edit!


(when (boundp 'msckf_vio::TrackingInfo)
  (if (not (find-package "MSCKF_VIO"))
    (make-package "MSCKF_VIO"))
  (shadow 'TrackingInfo (find-package "MSCKF_VIO")))
(unless (find-package "MSCKF_VIO::TRACKINGINFO")
  (make-package "MSCKF_VIO::TRACKINGINFO"))

(in-package "ROS")
;;//! \htmlinclude TrackingInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass msckf_vio::TrackingInfo
  :super ros::object
  :slots (_header _before_tracking _after_tracking _after_matching _after_ransac ))

(defmethod msckf_vio::TrackingInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:before_tracking __before_tracking) 0)
    ((:after_tracking __after_tracking) 0)
    ((:after_matching __after_matching) 0)
    ((:after_ransac __after_ransac) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _before_tracking (round __before_tracking))
   (setq _after_tracking (round __after_tracking))
   (setq _after_matching (round __after_matching))
   (setq _after_ransac (round __after_ransac))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:before_tracking
   (&optional __before_tracking)
   (if __before_tracking (setq _before_tracking __before_tracking)) _before_tracking)
  (:after_tracking
   (&optional __after_tracking)
   (if __after_tracking (setq _after_tracking __after_tracking)) _after_tracking)
  (:after_matching
   (&optional __after_matching)
   (if __after_matching (setq _after_matching __after_matching)) _after_matching)
  (:after_ransac
   (&optional __after_ransac)
   (if __after_ransac (setq _after_ransac __after_ransac)) _after_ransac)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int16 _before_tracking
    2
    ;; int16 _after_tracking
    2
    ;; int16 _after_matching
    2
    ;; int16 _after_ransac
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int16 _before_tracking
       (write-word _before_tracking s)
     ;; int16 _after_tracking
       (write-word _after_tracking s)
     ;; int16 _after_matching
       (write-word _after_matching s)
     ;; int16 _after_ransac
       (write-word _after_ransac s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int16 _before_tracking
     (setq _before_tracking (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _after_tracking
     (setq _after_tracking (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _after_matching
     (setq _after_matching (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _after_ransac
     (setq _after_ransac (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get msckf_vio::TrackingInfo :md5sum-) "fe61515ea4754478598919b321c32c28")
(setf (get msckf_vio::TrackingInfo :datatype-) "msckf_vio/TrackingInfo")
(setf (get msckf_vio::TrackingInfo :definition-)
      "std_msgs/Header header

# Number of features after each outlier removal step.
int16 before_tracking
int16 after_tracking
int16 after_matching
int16 after_ransac

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :msckf_vio/TrackingInfo "fe61515ea4754478598919b321c32c28")


