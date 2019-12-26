; Auto-generated. Do not edit!


(cl:in-package msckf_vio-msg)


;//! \htmlinclude FeatureMeasurement.msg.html

(cl:defclass <FeatureMeasurement> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (u0
    :reader u0
    :initarg :u0
    :type cl:float
    :initform 0.0)
   (v0
    :reader v0
    :initarg :v0
    :type cl:float
    :initform 0.0)
   (u1
    :reader u1
    :initarg :u1
    :type cl:float
    :initform 0.0)
   (v1
    :reader v1
    :initarg :v1
    :type cl:float
    :initform 0.0))
)

(cl:defclass FeatureMeasurement (<FeatureMeasurement>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FeatureMeasurement>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FeatureMeasurement)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name msckf_vio-msg:<FeatureMeasurement> is deprecated: use msckf_vio-msg:FeatureMeasurement instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <FeatureMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:id-val is deprecated.  Use msckf_vio-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'u0-val :lambda-list '(m))
(cl:defmethod u0-val ((m <FeatureMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:u0-val is deprecated.  Use msckf_vio-msg:u0 instead.")
  (u0 m))

(cl:ensure-generic-function 'v0-val :lambda-list '(m))
(cl:defmethod v0-val ((m <FeatureMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:v0-val is deprecated.  Use msckf_vio-msg:v0 instead.")
  (v0 m))

(cl:ensure-generic-function 'u1-val :lambda-list '(m))
(cl:defmethod u1-val ((m <FeatureMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:u1-val is deprecated.  Use msckf_vio-msg:u1 instead.")
  (u1 m))

(cl:ensure-generic-function 'v1-val :lambda-list '(m))
(cl:defmethod v1-val ((m <FeatureMeasurement>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader msckf_vio-msg:v1-val is deprecated.  Use msckf_vio-msg:v1 instead.")
  (v1 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FeatureMeasurement>) ostream)
  "Serializes a message object of type '<FeatureMeasurement>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 32) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 40) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 48) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 56) (cl:slot-value msg 'id)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'u0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'v0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'u1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'v1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FeatureMeasurement>) istream)
  "Deserializes a message object of type '<FeatureMeasurement>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 32) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 40) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 48) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 56) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'u0) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'v0) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'u1) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'v1) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FeatureMeasurement>)))
  "Returns string type for a message object of type '<FeatureMeasurement>"
  "msckf_vio/FeatureMeasurement")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FeatureMeasurement)))
  "Returns string type for a message object of type 'FeatureMeasurement"
  "msckf_vio/FeatureMeasurement")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FeatureMeasurement>)))
  "Returns md5sum for a message object of type '<FeatureMeasurement>"
  "db12fb5f7b2a7982c9988e36b7a4cd3f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FeatureMeasurement)))
  "Returns md5sum for a message object of type 'FeatureMeasurement"
  "db12fb5f7b2a7982c9988e36b7a4cd3f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FeatureMeasurement>)))
  "Returns full string definition for message of type '<FeatureMeasurement>"
  (cl:format cl:nil "uint64 id~%# Normalized feature coordinates (with identity intrinsic matrix)~%float64 u0 # horizontal coordinate in cam0~%float64 v0 # vertical coordinate in cam0~%float64 u1 # horizontal coordinate in cam0~%float64 v1 # vertical coordinate in cam0~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FeatureMeasurement)))
  "Returns full string definition for message of type 'FeatureMeasurement"
  (cl:format cl:nil "uint64 id~%# Normalized feature coordinates (with identity intrinsic matrix)~%float64 u0 # horizontal coordinate in cam0~%float64 v0 # vertical coordinate in cam0~%float64 u1 # horizontal coordinate in cam0~%float64 v1 # vertical coordinate in cam0~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FeatureMeasurement>))
  (cl:+ 0
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FeatureMeasurement>))
  "Converts a ROS message object to a list"
  (cl:list 'FeatureMeasurement
    (cl:cons ':id (id msg))
    (cl:cons ':u0 (u0 msg))
    (cl:cons ':v0 (v0 msg))
    (cl:cons ':u1 (u1 msg))
    (cl:cons ':v1 (v1 msg))
))
