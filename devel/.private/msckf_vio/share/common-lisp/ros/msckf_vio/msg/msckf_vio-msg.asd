
(cl:in-package :asdf)

(defsystem "msckf_vio-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "CameraMeasurement" :depends-on ("_package_CameraMeasurement"))
    (:file "_package_CameraMeasurement" :depends-on ("_package"))
    (:file "FeatureMeasurement" :depends-on ("_package_FeatureMeasurement"))
    (:file "_package_FeatureMeasurement" :depends-on ("_package"))
    (:file "Pose" :depends-on ("_package_Pose"))
    (:file "_package_Pose" :depends-on ("_package"))
    (:file "TrackingInfo" :depends-on ("_package_TrackingInfo"))
    (:file "_package_TrackingInfo" :depends-on ("_package"))
  ))