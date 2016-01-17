require 'rake/extensiontask'

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec)
task :default => :spec

Rake::ExtensionTask.new "rbzmq" do |ext|
  ext.lib_dir = "lib/rbzmq"
end

