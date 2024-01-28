# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'C++ 洋葱剥法交流群资料'
copyright = '2024, FeignClaims'
author = 'FeignClaims'
version = 'v1.0.0'
release = 'v1.0.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['sphinx_togglebutton', 'sphinx.ext.todo',
              'sphinx.ext.graphviz', 'sphinx.ext.extlinks', 'sphinx_rtd_theme']

extlinks = {'godbolt': ('https://godbolt.org/z/%s', '[在线代码 %s]'), 'coreguidelines': (
    'https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#%s', '[核心准则 %s]')}

togglebutton_hint = ""
togglebutton_hint_hide = ""

templates_path = ['_templates']
exclude_patterns = []

rst_prolog = '\n'.join(
    list(
        map(
            lambda filename: open(f'_static/{filename}', 'r', encoding="utf8").read(),
            ['inline_cpp.rst', 'links.rst']))) + '\n'

language = 'zh_CN'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_js_files = []
html_search_language = 'zh'
html_last_updated_fmt = '%Y-%m-%d %H:%M:%S %z'
