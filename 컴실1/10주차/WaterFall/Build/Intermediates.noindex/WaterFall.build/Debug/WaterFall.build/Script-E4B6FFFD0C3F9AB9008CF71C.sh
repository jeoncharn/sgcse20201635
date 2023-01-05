#!/bin/sh
mkdir -p "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources/"
# Copy default icon file into App/Resources
rsync -aved "$ICON_FILE" "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources/"
# Copy libfmod and change install directory for fmod to run
rsync -aved "$OF_PATH/libs/fmodex/lib/osx/libfmodex.dylib" "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Frameworks/";
install_name_tool -change @executable_path/libfmodex.dylib @executable_path/../Frameworks/libfmodex.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME";

echo "$GCC_PREPROCESSOR_DEFINITIONS";

