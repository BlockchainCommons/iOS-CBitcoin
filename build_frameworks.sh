#!/usr/bin/env bash

POD_ROOT="${PWD}"
SRC_ROOT="${POD_ROOT}/CBitcoin"
FRAMEWORKS_ROOT="${SRC_ROOT}/Frameworks"
DEPS_ROOT="${SRC_ROOT}/airbitz-core/deps"
DEPS_BUILD_ROOT="${DEPS_ROOT}/build"
BUILD_PATH="ios-universal/lib"

set -e

pushd () {
    command pushd "$@" > /dev/null
}

popd () {
    command popd "$@" > /dev/null
}

message() {
    echo "====" $1
}

build_framework() {
    BASE_PATH=$1
    FRAMEWORK_BASE_NAME=$2
    FRAMEWORK_BASE_IDENTIFIER=$3
    SOURCE_STATIC_LIBRARY_PATH=$4
    SOURCE_HEADERS=$5

    FRAMEWORK_NAME="${FRAMEWORK_BASE_NAME}.framework"
    FRAMEWORK_PATH="${BASE_PATH}/${FRAMEWORK_NAME}"
    STATIC_LIBRARY_PATH="${FRAMEWORK_PATH}/${FRAMEWORK_BASE_NAME}"
    RESOURCES_PATH="${FRAMEWORK_PATH}/Resources"
    HEADERS_PATH="${FRAMEWORK_PATH}/Headers"
    INFO_PLIST_PATH="${RESOURCES_PATH}/Info.plist"

    rm -rf "${FRAMEWORK_PATH}"
    mkdir -p "${FRAMEWORK_PATH}"
    cp "${SOURCE_STATIC_LIBRARY_PATH}" "${STATIC_LIBRARY_PATH}"
    mkdir "${RESOURCES_PATH}"
    mkdir "${HEADERS_PATH}"

    defaults write "${INFO_PLIST_PATH}" CFBundleName "${FRAMEWORK_BASE_NAME}"
    defaults write "${INFO_PLIST_PATH}" CFBundleDevelopmentRegion en
    defaults write "${INFO_PLIST_PATH}" CFBundleVersion 1
    defaults write "${INFO_PLIST_PATH}" CFBundlePackageType FMWK
    defaults write "${INFO_PLIST_PATH}" CFBundleShortVersionString "1.0"
    defaults write "${INFO_PLIST_PATH}" CFBundleInfoDictionaryVersion "6.0"
    defaults write "${INFO_PLIST_PATH}" CFBundleExecutable "${FRAMEWORK_BASE_NAME}"
    defaults write "${INFO_PLIST_PATH}" CFBundleIdentifier "${FRAMEWORK_BASE_IDENTIFIER}.${FRAMEWORK_BASE_NAME}"

    cp -r ${SOURCE_HEADERS} "${HEADERS_PATH}/" # Globbing happens here
}

start() {
    pushd .
}

finish() {
    popd .
}

build_libbitcoin() {
    message "Building libbitcoin and dependencies"
    cd ${DEPS_ROOT}
    make libbitcoin.ios-universal
}

build_breadwalletcore() {
    message "Building Breadwallet Core and dependencies"
    cd ${DEPS_ROOT}
    make breadwalletcore.ios-universal
}

build_sss() {
    message "Building sss and dependencies"
    cd ${DEPS_ROOT}
    make sss.ios-universal
}

build_libboost_framework() {
    message "Building libboost.framework"

    LIB_ROOT="${DEPS_BUILD_ROOT}/boost"
    LIB_NAME="libboost"

    LIB_BUILD_ROOT="${LIB_ROOT}/${BUILD_PATH}"
    STATIC_LIBRARY_PATH="${LIB_BUILD_ROOT}/${LIB_NAME}.a"
    # merge boost static libraries
    rm -f "${STATIC_LIBRARY_PATH}"
    cd "${LIB_BUILD_ROOT}"
    libtool -static -no_warning_for_no_symbols -o "${STATIC_LIBRARY_PATH}" \
        libboost_atomic.a libboost_chrono.a libboost_date_time.a \
        libboost_filesystem.a libboost_program_options.a libboost_regex.a \
        libboost_system.a libboost_thread.a &>/dev/null

    HEADERS="${LIB_ROOT}/ios-armv7/boost_1_62_0/boost"

    build_framework "${FRAMEWORKS_ROOT}" "${LIB_NAME}" blockchaincommons "${STATIC_LIBRARY_PATH}" "${HEADERS}"
}

build_libsecp256k1_framework() {
    message "Building libsecp256k1.framework"

    LIB_ROOT="${DEPS_BUILD_ROOT}/libsecp256k1"
    LIB_NAME="libsecp256k1"

    STATIC_LIBRARY_PATH="${LIB_ROOT}/${BUILD_PATH}/${LIB_NAME}.a"
    HEADERS="${LIB_ROOT}/ios-armv7/include/*"

    build_framework "${FRAMEWORKS_ROOT}" "${LIB_NAME}" blockchaincommons "${STATIC_LIBRARY_PATH}" "${HEADERS}"
}

build_libbitcoin_framework() {
    message "Building libbitcoin.framework"

    LIB_ROOT="${DEPS_BUILD_ROOT}/libbitcoin"
    LIB_NAME="libbitcoin"

    STATIC_LIBRARY_PATH="${LIB_ROOT}/${BUILD_PATH}/${LIB_NAME}.a"
    HEADERS="${LIB_ROOT}/ios-armv7/include/*"

    build_framework "${FRAMEWORKS_ROOT}" "${LIB_NAME}" blockchaincommons "${STATIC_LIBRARY_PATH}" "${HEADERS}"
}

build_breadwalletcore_framework() {
    message "Building breadwalletcore.framework"

    LIB_ROOT="${DEPS_BUILD_ROOT}/breadwalletcore"
    LIB_NAME="breadwalletcore"

    STATIC_LIBRARY_PATH="${LIB_ROOT}/${BUILD_PATH}/${LIB_NAME}.a"
    HEADERS="${DEPS_BUILD_ROOT}/prefix/ios/armv7/include/${LIB_NAME}/*"

    build_framework "${FRAMEWORKS_ROOT}" "${LIB_NAME}" blockchaincommons "${STATIC_LIBRARY_PATH}" "${HEADERS}"
}

build_sss_framework() {
    message "Building libsss.framework"

    LIB_ROOT="${DEPS_BUILD_ROOT}/sss"
    LIB_NAME="libsss"

    STATIC_LIBRARY_PATH="${LIB_ROOT}/${BUILD_PATH}/${LIB_NAME}.a"
    HEADERS="${DEPS_BUILD_ROOT}/prefix/ios/armv7/include/${LIB_NAME}/*"

    build_framework "${FRAMEWORKS_ROOT}" "${LIB_NAME}" blockchaincommons "${STATIC_LIBRARY_PATH}" "${HEADERS}"
}

zip_frameworks() {
    message "Zipping Frameworks"

    pushd "${SRC_ROOT}"
    rm -f "Frameworks.zip"
    zip -qr Frameworks Frameworks
    popd
}

start
trap finish ERR

build_libbitcoin
build_breadwalletcore
build_sss

build_libboost_framework
build_libsecp256k1_framework
build_libbitcoin_framework
build_breadwalletcore_framework
build_sss_framework

zip_frameworks

finish
