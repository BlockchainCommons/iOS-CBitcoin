# CBitcoin

[![CI Status](https://img.shields.io/travis/wolfmcnally/CBitcoin.svg?style=flat)](https://travis-ci.org/wolfmcnally/CBitcoin)
[![Version](https://img.shields.io/cocoapods/v/CBitcoin.svg?style=flat)](https://cocoapods.org/pods/CBitcoin)
[![License](https://img.shields.io/cocoapods/l/CBitcoin.svg?style=flat)](https://cocoapods.org/pods/CBitcoin)
[![Platform](https://img.shields.io/cocoapods/p/CBitcoin.svg?style=flat)](https://cocoapods.org/pods/CBitcoin)

C bindings for [libbitcoin](https://github.com/libbitcoin). Intended primarily as support for the [Bitcoin](https://github.com/BlockchainCommons/iOS-Bitcoin) framework, which depends on this one and provides Swift bindings for libbitcoin.

## Requirements

* Swift 4.2

* This distribution includes pre-built fat frameworks for `libbitcoin` and its dependencies: `libboost`, and `libsecp256k1`. In order to check out this large pre-built file, you need to install the latest version of Git and the Git Large File Storage handler:

```bash
$ brew install git
$ brew install git-lfs
$ which git
/usr/local/bin/git
$ git --version
git version 2.20.1
```

## Unit Tests

Tests for CBitcoin are available in the Bitcoin framework.

## Installation

CBitcoin is available through [Cocoapads](https://cocoapods.org). To install it, add the following line to your Podfile:

```ruby
pod 'CBitcoin'
```

## Building the frameworks yourself

If you wish, you can run the included `build_frameworks.sh` script to build the frameworks for `libbitcoin`, `libboost`, and `libsecp256k1` from scratch. This will take significant time.

## Author

Wolf McNally, wolf@wolfmcnally.com

## License

CBitcoin is available under the MIT license. See the LICENSE file for more info.
