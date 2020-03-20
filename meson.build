project('munit_plus', 'cpp',
  default_options : ['cpp_std=c++11'])

conf_data = configuration_data()
conf_data.set('version', '0.2.0')

cxx = meson.get_compiler('cpp')

root_include = include_directories('.')

munit_plus = library('munit_plus',
    ['munit.cpp'],
    install: meson.is_subproject())

if meson.is_subproject()
  munit_plus_dep = declare_dependency(
      include_directories : root_include,
      link_with : munit)
else
  # standalone install
  install_headers('munit.hpp')

  pkg = import('pkgconfig')
  pkg.generate(name: 'munit_plus',
                description: 'µnit-plus Testing Library for C++',
                version: conf_data.get('version'),
                libraries: munit_plus)

  # compile the demo project
  munit_plus_example_src = files('example.cpp')
  munit_plus_example = executable('munit_plus_example', munit_plus_example_src,
              include_directories: root_include,
              link_with: munit_plus)

  test('munit-plus example test', munit_plus_example)
endif
