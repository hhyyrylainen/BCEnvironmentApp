require 'os'

require_relative 'RubySetupSystem/Libraries/SetupWt.rb'

# Setup dependencies settings
THIRD_PARTY_INSTALL = File.join(ProjectDir, 'build', 'ThirdParty')

@wt = Wt.new(
  version: '4.2.0',
  installPath: THIRD_PARTY_INSTALL,
  noInstallSudo: true,
  noExamples: true,
  shared: OS.windows? ? false : true,
  noQt: true
)

@libs_list = [@wt]
