; Auto-generated. Do not edit!


(cl:in-package msckf_vio-msg)


;//! \htmlinclude CameraMeasurement.msg.html

(cl:defclass <CameraMeasurement> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (features
    :reader features
    :initarg :features
    :type (cl:vector msckf_vio-msg:FeatureMeasurement)
   :initform (cl:make-array 0 :element-type 'msckf_vio-msg:FeatureMeasurement :initial-element (cl:make-instance 'msckf_vio-msg:FeatureMeasurement))))
)

(cl:defclass CameraMeasurement (<CameraMeasurement>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CameraMeasurement>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CameraMeasurement)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msckf_vio-msg:<CameraMeasurement> is deprecated: use msckf_vio-msg:CameraMeasurement instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CameraMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:header-val is deprecated.  Use msckf_vio-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'features-val :lambda-list '(m))
(cl:defmethod features-val ((m <CameraMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:features-val is deprecated.  Use msckf_vio-msg:features instead.")
  (features m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CameraMeasurement>) ostream)
  "Serializes a message object of type '<CameraMeasurement>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'features))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'features))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CameraMeasurement>) istream)
  "Deserializes a message object of type '<CameraMeasurement>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'features) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'features)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'msckf_vio-msg:FeatureMeasurement))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CameraMeasurement>)))
  "Returns string type for a message object of type '<CameraMeasurement>"
  "msckf_vio/CameraMeasurement")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CameraMeasurement)))
  "Returns string type for a message object of type 'CameraMeasurement"
  "msckf_vio/CameraMeasurement")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CameraMeasurement>)))
  "Returns md5sum for a message object of type '<CameraMeasurement>"
  "49e471535134556a8117bc01f9d9b57d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CameraMeasurement)))
  "Returns md5sum for a message object of type 'CameraMeasurement"
  "49e471535134556a8117bc01f9d9b57d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CameraMeasurement>)))
  "Returns full string definition for message of type '<CameraMeasurement>"
  (cl:format cl:nil "std_msgs/Header header~%# All features on the current image,~%# including tracked ones and newly detected ones.~%FeatureMeasurement[] features~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: msckf_vio/FeatureMeasurement~%uint64 id~%# Normalized feature coordinates (with identity intrinsic matrix)~%float64 u0 # horizontal coordinate in cam0~%float64 v0 # vertical coordinate in cam0~%float64 u1 # horizontal coordinate in cam0~%float64 v1 # vertical coordinate in cam0~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CameraMeasurement)))
  "Returns full string definition for message of type 'CameraMeasurement"
  (cl:format cl:nil "std_msgs/Header header~%# All features on the current image,~%# including tracked ones and newly detected ones.~%FeatureMeasurement[] features~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: msckf_vio/FeatureMeasurement~%uint64 id~%# Normalized feature coordinates (with identity intrinsic matrix)~%float64 u0 # horizontal coordinate in cam0~%float64 v0 # vertical coordinate in cam0~%float64 u1 # horizontal coordinate in cam0~%float64 v1 # vertical coordinate in cam0~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CameraMeasurement>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'features) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CameraMeasurement>))
  "Converts a ROS message object to a list"
  (cl:list 'CameraMeasurement
    (cl:cons ':header (header msg))
    (cl:cons ':features (features msg))
))
