Pod::Spec.new do |s|
    s.name             = 'CBitcoin'
    s.version          = '0.4.0'
    s.summary          = 'C Bindings for libbitcoin, breadwalletcore, and sss (Shamir Secret Sharing).'

    # s.description      = <<-DESC
    # TODO: Add long description of the pod here.
    # DESC

    s.homepage         = 'https://github.com/blockchaincommons/iOS-CBitcoin'
    s.license          = { :type => 'Apache', :file => 'LICENSE' }
    s.author           = { 'Wolf McNally' => 'wolf@wolfmcnally.com' }
    s.source           = { :git => 'https://github.com/blockchaincommons/iOS-CBitcoin.git', :tag => s.version.to_s }

    s.swift_version = '5.0'

    s.source_files = 'CBitcoin/Classes/**/*'
    s.private_header_files = 'CBitcoin/Classes/Private/**/*.hpp'
    s.vendored_frameworks = 'CBitcoin/Frameworks/*'
    s.pod_target_xcconfig = { \
        'OTHER_CFLAGS' => '-w', \
        'HEADER_SEARCH_PATHS' => '$(inherited) "${PODS_TARGET_SRCROOT}/CBitcoin/Frameworks/libboost.framework/Headers" "${PODS_TARGET_SRCROOT}/CBitcoin/Frameworks/libsecp256k1.framework/Headers" "${PODS_TARGET_SRCROOT}/CBitcoin/Frameworks/libbitcoin.framework/Headers" "${PODS_TARGET_SRCROOT}/CBitcoin/Frameworks/breadwalletcore.framework/Headers" "${PODS_TARGET_SRCROOT}/CBitcoin/Frameworks/libsss.framework/Headers"' }

    s.ios.deployment_target = '11.0'
    #s.macos.deployment_target = '10.13'
    #s.tvos.deployment_target = '11.0'

    s.module_name = 'CBitcoin'

    s.prepare_command = <<-CMD
            pushd CBitcoin
            rm -rf Frameworks/
            unzip -o -q Frameworks.zip
            popd
        CMD
end
