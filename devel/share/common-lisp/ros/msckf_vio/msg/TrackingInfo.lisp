; Auto-generated. Do not edit!


(cl:in-package msckf_vio-msg)


;//! \htmlinclude TrackingInfo.msg.html

(cl:defclass <TrackingInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (before_tracking
    :reader before_tracking
    :initarg :before_tracking
    :type cl:fixnum
    :initform 0)
   (after_tracking
    :reader after_tracking
    :initarg :after_tracking
    :type cl:fixnum
    :initform 0)
   (after_matching
    :reader after_matching
    :initarg :after_matching
    :type cl:fixnum
    :initform 0)
   (after_ransac
    :reader after_ransac
    :initarg :after_ransac
    :type cl:fixnum
    :initform 0))
)

(cl:defclass TrackingInfo (<TrackingInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TrackingInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TrackingInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msckf_vio-msg:<TrackingInfo> is deprecated: use msckf_vio-msg:TrackingInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <TrackingInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:header-val is deprecated.  Use msckf_vio-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'before_tracking-val :lambda-list '(m))
(cl:defmethod before_tracking-val ((m <TrackingInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:before_tracking-val is deprecated.  Use msckf_vio-msg:before_tracking instead.")
  (before_tracking m))

(cl:ensure-generic-function 'after_tracking-val :lambda-list '(m))
(cl:defmethod after_tracking-val ((m <TrackingInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:after_tracking-val is deprecated.  Use msckf_vio-msg:after_tracking instead.")
  (after_tracking m))

(cl:ensure-generic-function 'after_matching-val :lambda-list '(m))
(cl:defmethod after_matching-val ((m <TrackingInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:after_matching-val is deprecated.  Use msckf_vio-msg:after_matching instead.")
  (after_matching m))

(cl:ensure-generic-function 'after_ransac-val :lambda-list '(m))
(cl:defmethod after_ransac-val ((m <TrackingInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:after_ransac-val is deprecated.  Use msckf_vio-msg:after_ransac instead.")
  (after_ransac m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TrackingInfo>) ostream)
  "Serializes a message object of type '<TrackingInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'before_tracking)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'after_tracking)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'after_matching)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'after_ransac)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TrackingInfo>) istream)
  "Deserializes a message object of type '<TrackingInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'before_tracking) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'after_tracking) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'after_matching) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'after_ransac) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TrackingInfo>)))
  "Returns string type for a message object of type '<TrackingInfo>"
  "msckf_vio/TrackingInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TrackingInfo)))
  "Returns string type for a message object of type 'TrackingInfo"
  "msckf_vio/TrackingInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TrackingInfo>)))
  "Returns md5sum for a message object of type '<TrackingInfo>"
  "fe61515ea4754478598919b321c32c28")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TrackingInfo)))
  "Returns md5sum for a message object of type 'TrackingInfo"
  "fe61515ea4754478598919b321c32c28")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TrackingInfo>)))
  "Returns full string definition for message of type '<TrackingInfo>"
  (cl:format cl:nil "std_msgs/Header header~%~%# Number of features after each outlier removal step.~%int16 before_tracking~%int16 after_tracking~%int16 after_matching~%int16 after_ransac~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TrackingInfo)))
  "Returns full string definition for message of type 'TrackingInfo"
  (cl:format cl:nil "std_msgs/Header header~%~%# Number of features after each outlier removal step.~%int16 before_tracking~%int16 after_tracking~%int16 after_matching~%int16 after_ransac~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TrackingInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     2
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TrackingInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'TrackingInfo
    (cl:cons ':header (header msg))
    (cl:cons ':before_tracking (before_tracking msg))
    (cl:cons ':after_tracking (after_tracking msg))
    (cl:cons ':after_matching (after_matching msg))
    (cl:cons ':after_ransac (after_ransac msg))
))
