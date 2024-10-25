# Install script for directory: U:/DSI-Studio-master/TIPL

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/TIPL")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" TYPE FILE FILES "U:/DSI-Studio-master/TIPL/build/tipl.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/def.hpp"
    "U:/DSI-Studio-master/TIPL/mt.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/TIPL" TYPE FILE FILES "U:/DSI-Studio-master/TIPL/tipl.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/filter" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/filter/anisotropic_diffusion.hpp"
    "U:/DSI-Studio-master/TIPL/filter/canny_edge.hpp"
    "U:/DSI-Studio-master/TIPL/filter/filter_model.hpp"
    "U:/DSI-Studio-master/TIPL/filter/gaussian.hpp"
    "U:/DSI-Studio-master/TIPL/filter/gradient_magnitude.hpp"
    "U:/DSI-Studio-master/TIPL/filter/laplacian.hpp"
    "U:/DSI-Studio-master/TIPL/filter/mean.hpp"
    "U:/DSI-Studio-master/TIPL/filter/sobel.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/io" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/io/2dseq.hpp"
    "U:/DSI-Studio-master/TIPL/io/avi.hpp"
    "U:/DSI-Studio-master/TIPL/io/bitmap.hpp"
    "U:/DSI-Studio-master/TIPL/io/dicom.hpp"
    "U:/DSI-Studio-master/TIPL/io/gz_stream.hpp"
    "U:/DSI-Studio-master/TIPL/io/interface.hpp"
    "U:/DSI-Studio-master/TIPL/io/mat.hpp"
    "U:/DSI-Studio-master/TIPL/io/nifti.hpp"
    "U:/DSI-Studio-master/TIPL/io/nrrd.hpp"
    "U:/DSI-Studio-master/TIPL/io/tiff.hpp"
    "U:/DSI-Studio-master/TIPL/io/tiff_tag.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ml" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/ml/ada_boost.hpp"
    "U:/DSI-Studio-master/TIPL/ml/cnn.hpp"
    "U:/DSI-Studio-master/TIPL/ml/cnn3d.hpp"
    "U:/DSI-Studio-master/TIPL/ml/decision_tree.hpp"
    "U:/DSI-Studio-master/TIPL/ml/em.hpp"
    "U:/DSI-Studio-master/TIPL/ml/hmc.hpp"
    "U:/DSI-Studio-master/TIPL/ml/k_means.hpp"
    "U:/DSI-Studio-master/TIPL/ml/lg.hpp"
    "U:/DSI-Studio-master/TIPL/ml/nb.hpp"
    "U:/DSI-Studio-master/TIPL/ml/non_parametric.hpp"
    "U:/DSI-Studio-master/TIPL/ml/unet3d.hpp"
    "U:/DSI-Studio-master/TIPL/ml/utility.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/morphology" TYPE FILE FILES "U:/DSI-Studio-master/TIPL/morphology/morphology.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/numerical" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/numerical/basic_op.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/dif.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/fft.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/index_algorithm.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/interpolation.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/matrix.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/numerical.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/optimization.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/resampling.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/statistics.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/transformation.hpp"
    "U:/DSI-Studio-master/TIPL/numerical/window.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/reg" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/reg/bfnorm.hpp"
    "U:/DSI-Studio-master/TIPL/reg/cdm.hpp"
    "U:/DSI-Studio-master/TIPL/reg/linear.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/segmentation" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/segmentation/disjoint_set.hpp"
    "U:/DSI-Studio-master/TIPL/segmentation/fast_marching.hpp"
    "U:/DSI-Studio-master/TIPL/segmentation/graph_cut.hpp"
    "U:/DSI-Studio-master/TIPL/segmentation/otsu.hpp"
    "U:/DSI-Studio-master/TIPL/segmentation/segmentation.hpp"
    "U:/DSI-Studio-master/TIPL/segmentation/watershed.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/utility" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/utility/basic_image.hpp"
    "U:/DSI-Studio-master/TIPL/utility/pixel_index.hpp"
    "U:/DSI-Studio-master/TIPL/utility/rgb_image.hpp"
    "U:/DSI-Studio-master/TIPL/utility/shape.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vis" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/vis/color_map.hpp"
    "U:/DSI-Studio-master/TIPL/vis/march_cube.hpp"
    "U:/DSI-Studio-master/TIPL/vis/qt_ext.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TIPL/TIPLTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TIPL/TIPLTargets.cmake"
         "U:/DSI-Studio-master/TIPL/build/CMakeFiles/Export/d702eb15ddbaf61f3bed825ea98da2bf/TIPLTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TIPL/TIPLTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/TIPL/TIPLTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/TIPL" TYPE FILE FILES "U:/DSI-Studio-master/TIPL/build/CMakeFiles/Export/d702eb15ddbaf61f3bed825ea98da2bf/TIPLTargets.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/TIPL" TYPE FILE FILES
    "U:/DSI-Studio-master/TIPL/build/TIPLConfigVersion.cmake"
    "U:/DSI-Studio-master/TIPL/build/TIPLConfig.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "U:/DSI-Studio-master/TIPL/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
