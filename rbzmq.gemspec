lib = File.expand_path('../lib/', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)

require 'rbzmq/version'

Gem::Specification.new do |s|
  s.name        = 'rbzmq'
  s.version     = 'ZMQ::VERSION'
  s.summary     = 'Ruby bindings for 0MQ'
  s.description = 'A ruby binding for the latest 0MQ version (4.2)'
  s.authors     = [ 'Francesco Boffa' ]
  s.email       = 'fra.boffa@gmail.com'
  s.homepage    = 'https://github.com/aomega08/rbzmq'
  s.license     = 'MIT'

  s.files = `git ls-files`.split("\n")
  s.require_paths = %w(lib)

  s.add_development_dependency 'rspec'
  s.add_development_dependency 'rake'
  s.add_development_dependency 'codeclimate-test-reporter'
end

