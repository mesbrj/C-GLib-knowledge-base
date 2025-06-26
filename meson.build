project('glib-demo', 'c',
  version : '1.0.0',
  default_options : ['warning_level=3',
                     'c_std=c11'])

# Find GLib dependency
glib_dep = dependency('glib-2.0', version : '>=2.50')

# Include directory
inc_dir = include_directories('src')

# Build shared library for GLib features
glib_features_lib = shared_library('glib_features',
  'src/test_double_linked_lists.c',
  'src/test_hash_tables.c',
  'src/test_async_queue.c',
  dependencies : glib_dep,
  include_directories : inc_dir,
  install : true)

# Build main test program
executable('app_test',
  'src/test_menu.c',
  dependencies : glib_dep,
  link_with : glib_features_lib,
  include_directories : inc_dir,
  install : true)