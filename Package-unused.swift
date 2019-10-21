// swift-tools-version:5.0
import PackageDescription

let package = Package(
    name: "CBitcoin",
    platforms: [
        .iOS(.v11), .macOS(.v10_13), .tvOS(.v11)
    ],
    products: [
        .library(name: "CBitcoin", targets: ["CBitcoin"])
    ],
    targets: [
        .target(
          name: "CBitcoin",
          cSettings: [
            .headerSearchPath("Sources/Frameworks/libsss.framework/Headers"),
          ],
          cxxSettings: [
            .headerSearchPath("Sources/Frameworks/libbitcoin.framework/Headers"),
            .headerSearchPath("Sources/CBitcoin/Private"),
            .headerSearchPath("Sources/Frameworks/libboost.framework/headers"),
          ],
          linkerSettings: [
            .unsafeFlags([
              "-FSources/Frameworks"
            ]),
            .linkedFramework("libsss"),
            .linkedFramework("libbitcoin"),
            .linkedFramework("libsecp256k1"),
            .linkedFramework("libboost"),
          ]
        )
    ],
    cxxLanguageStandard: .cxx11
)
