#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <string>

namespace sharp {

  enum class ImageType {
    UNKNOWN,
    JPEG,
    PNG,
    WEBP,
    TIFF,
    MAGICK,
    OPENSLIDE
  };

  // How many tasks are in the queue?
  extern volatile int counterQueue;

  // How many tasks are being processed?
  extern volatile int counterProcess;

  // Filename extension checkers
  bool IsJpeg(std::string const &str);
  bool IsPng(std::string const &str);
  bool IsWebp(std::string const &str);
  bool IsTiff(std::string const &str);
  bool IsDz(std::string const &str);

  /*
    Determine image format of a buffer.
  */
  ImageType DetermineImageType(void *buffer, size_t const length);

  /*
    Determine image format of a file.
  */
  ImageType DetermineImageType(char const *file);

  /*
    Initialise and return a VipsImage from a buffer. Supports JPEG, PNG, WebP and TIFF.
  */
  VipsImage* InitImage(void *buffer, size_t const length, VipsAccess const access);

  /*
    Initialise and return a VipsImage from a file.
  */
  VipsImage* InitImage(char const *file, VipsAccess const access);

  /*
    Does this image have an embedded profile?
  */
  bool HasProfile(VipsImage *image);

  /*
    Does this image have an alpha channel?
    Uses colour space interpretation with number of channels to guess this.
  */
  bool HasAlpha(VipsImage *image);

  /*
    Get EXIF Orientation of image, if any.
  */
  int ExifOrientation(VipsImage const *image);

  /*
    Set EXIF Orientation of image.
  */
  void SetExifOrientation(VipsImage *image, int const orientation);

  /*
    Remove EXIF Orientation from image.
  */
  void RemoveExifOrientation(VipsImage *image);

  /*
    Returns the window size for the named interpolator. For example,
    a window size of 3 means a 3x3 pixel grid is used for the calculation.
  */
  int InterpolatorWindowSize(char const *name);

  /*
    Called when a Buffer undergoes GC, required to support mixed runtime libraries in Windows
  */
  void FreeCallback(char* data, void* hint);

}  // namespace sharp

#endif  // SRC_COMMON_H_
