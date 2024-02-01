# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'C++ 洋葱剥法交流群资料'
copyright = '2024, FeignClaims'
author = 'FeignClaims'
html_title = f'{project}'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.extlinks',
    'sphinx.ext.graphviz',
    'sphinx.ext.todo',
    'sphinx_copybutton',
    'sphinx_design',
    'sphinx_examples',
    'sphinx_last_updated_by_git',
    'sphinx_tabs.tabs',
    'sphinx_togglebutton',
]

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

html_copy_source = False
html_show_sourcelink = False

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_book_theme'
html_theme_options = {
    'repository_url': 'https://github.com/FeignClaims/question_board',
    'path_to_docs': 'docs/',
    'use_source_button': True,
    'use_edit_page_button': True,
    'use_issues_button': True,
    'show_prev_next': False,
    'show_nav_level': 0,
    'show_toc_level': 2,
    "icon_links": [
        {
            "name": "GitHub",
            "url": "https://github.com/FeignClaims/question_board",
            "icon": "fa-brands fa-github",
        },
        {
            "name": "部署状态",
            "url": "https://readthedocs.org/projects/question-board/",
            "icon": "https://readthedocs.org/projects/question-board/badge/?version=latest",
            "type": "url",
        }
    ],
}
html_static_path = ['_static']
html_favicon = '_static/favicon.png'
html_search_language = 'zh'
html_last_updated_fmt = '%Y-%m-%d %H:%M:%S'
git_last_updated_timezone = 'Asia/Shanghai'


def setup(app):
    app.add_css_file("coreguidelines.css")
    app.add_css_file("monofont.css")
    app.add_css_file("theme.css")
