# CBitcoin

[![CI Status](https://img.shields.io/travis/wolfmcnally/CBitcoin.svg?style=flat)](https://travis-ci.org/wolfmcnally/CBitcoin)
[![Version](https://img.shields.io/cocoapods/v/CBitcoin.svg?style=flat)](https://cocoapods.org/pods/CBitcoin)
[![License](https://img.shields.io/cocoapods/l/CBitcoin.svg?style=flat)](https://cocoapods.org/pods/CBitcoin)
[![Platform](https://img.shields.io/cocoapods/p/CBitcoin.svg?style=flat)](https://cocoapods.org/pods/CBitcoin)

C bindings for [libbitcoin](https://github.com/libbitcoin). Intended primarily as support for the [Bitcoin](https://github.com/BlockchainCommons/iOS-Bitcoin) framework, which depends on this one and provides Swift bindings for libbitcoin.

## Blog Post

On January 25, 2019 I published an announcement for this framework on my blog [here](https://wolfmcnally.com/125/announcing-open-source-bitcoin-framework-for-ios/).

## Requirements

* Swift 5

* This distribution includes pre-built fat frameworks for `libbitcoin` and its dependencies: `libboost`, and `libsecp256k1`. In order to check out this large pre-built file, you need to install the latest version of Git and the Git Large File Storage handler:

```bash
$ brew install git
$ brew install git-lfs
$ which git
/usr/local/bin/git
$ git --version
git version 2.20.1
```

## Installation

CBitcoin no longer supports building via Cocoapods, but since it also relies on embedding several third-party pre-built binary frameworks (libbitcoin etc.) it is also not suitable for distribution via the Swift Package Manager at this time. So for now, it is built directly as an Xcode project.

In the shell:

```bash
$ git clone https://github.com/BlockchainCommons/iOS-CBitcoin.git CBitcoin
$ cd CBitcoin/Sources
$ unzip -q Frameworks.zip
$ cd ..
$ open CBitcoin.xcodeproj/
```

Within Xcode:

* Build the `CBitcoin` target for an available platform.

## Unit Tests

`CBitcoin` does not have built-in unit tests, but the `Bitcoin` Swift framework builds on `CBitcoin` and contains unit tests for all `CBitcoin` functionality.

## Building the frameworks yourself

If you wish, you can run the included `build_frameworks.sh` script to build the frameworks for `libbitcoin`, `libboost`, and `libsecp256k1` from scratch. This will take significant time.

## Author

Wolf McNally, wolf@wolfmcnally.com

## License

CBitcoin is available under the MIT license. See the LICENSE file for more info.
