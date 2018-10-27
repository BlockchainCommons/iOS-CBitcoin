Pod::Spec.new do |s|
    s.name             = 'CBitcoin'
    s.version          = '0.1.0'
    s.summary          = 'C Bindings for libbitcoin.'

    # s.description      = <<-DESC
    # TODO: Add long description of the pod here.
    # DESC

    s.homepage         = 'https://github.com/blockchaincommons/iOS-CBitcoin'
    s.license          = { :type => 'MIT', :file => 'LICENSE' }
    s.author           = { 'Wolf McNally' => 'wolf@wolfmcnally.com' }
    s.source           = { :git => 'https://github.com/blockchaincommons/iOS-CBitcoin', :tag => s.version.to_s }

    s.swift_version = '4.2'

    s.source_files = 'CBitcoin/Classes/**/*'
    s.private_header_files = 'CBitcoin/Classes/Private/**/*'
    s.vendored_frameworks = 'CBitcoin/Frameworks/*'
    s.pod_target_xcconfig = { \
        'OTHER_CFLAGS' => '-w', \
        'HEADER_SEARCH_PATHS' => '$(inherited) "${PODS_TARGET_SRCROOT}/CBitcoin/Frameworks/libboost.framework/Headers" "${PODS_TARGET_SRCROOT}/CBitcoin/Frameworks/libsecp256k1.framework/Headers" "${PODS_TARGET_SRCROOT}/CBitcoin/Frameworks/libbitcoin.framework/Headers"' }

    s.ios.deployment_target = '9.3'

    s.module_name = 'CBitcoin'

    #s.dependency 'WolfPipe'
end