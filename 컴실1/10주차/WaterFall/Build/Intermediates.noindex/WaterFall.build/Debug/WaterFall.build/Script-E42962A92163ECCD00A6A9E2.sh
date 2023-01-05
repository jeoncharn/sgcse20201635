#!/bin/sh
xcodebuild -project "$OF_PATH/libs/openFrameworksCompiled/project/osx/openFrameworksLib.xcodeproj" -target openFrameworks -configuration "${CONFIGURATION}"
