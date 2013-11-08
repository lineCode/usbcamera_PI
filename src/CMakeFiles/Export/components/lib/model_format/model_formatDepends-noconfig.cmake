#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "model_format" for configuration ""
SET_PROPERTY(TARGET model_format APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(model_format PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "pthread;omniORB4;omnithread;omniDynamic4;RTC;coil;/usr/local/opencv2.4.5/lib/libopencv_calib3d.so;/usr/local/opencv2.4.5/lib/libopencv_contrib.so;/usr/local/opencv2.4.5/lib/libopencv_core.so;/usr/local/opencv2.4.5/lib/libopencv_features2d.so;/usr/local/opencv2.4.5/lib/libopencv_flann.so;/usr/local/opencv2.4.5/lib/libopencv_gpu.so;/usr/local/opencv2.4.5/lib/libopencv_highgui.so;/usr/local/opencv2.4.5/lib/libopencv_imgproc.so;/usr/local/opencv2.4.5/lib/libopencv_legacy.so;/usr/local/opencv2.4.5/lib/libopencv_ml.so;/usr/local/opencv2.4.5/lib/libopencv_nonfree.so;/usr/local/opencv2.4.5/lib/libopencv_objdetect.so;/usr/local/opencv2.4.5/lib/libopencv_photo.so;/usr/local/opencv2.4.5/lib/libopencv_stitching.so;/usr/local/opencv2.4.5/lib/libopencv_superres.so;/usr/local/opencv2.4.5/lib/libopencv_ts.so;/usr/local/opencv2.4.5/lib/libopencv_video.so;/usr/local/opencv2.4.5/lib/libopencv_videostab.so"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/model_format.so"
  IMPORTED_SONAME_NOCONFIG "model_format.so"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS model_format )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_model_format "${_IMPORT_PREFIX}/components/lib/model_format.so" )

# Import target "model_formatComp" for configuration ""
SET_PROPERTY(TARGET model_formatComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(model_formatComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/model_formatComp"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS model_formatComp )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_model_formatComp "${_IMPORT_PREFIX}/components/bin/model_formatComp" )

# Loop over all imported files and verify that they actually exist
FOREACH(target ${_IMPORT_CHECK_TARGETS} )
  FOREACH(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    IF(NOT EXISTS "${file}" )
      MESSAGE(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    ENDIF()
  ENDFOREACH()
  UNSET(_IMPORT_CHECK_FILES_FOR_${target})
ENDFOREACH()
UNSET(_IMPORT_CHECK_TARGETS)

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
