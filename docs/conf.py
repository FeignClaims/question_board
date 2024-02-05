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
    'sphinx_sitemap',
    'sphinx_tabs.tabs',
    'sphinx_togglebutton',
]

extlinks = {'godbolt': ('https://godbolt.org/z/%s', '[在线代码 %s]'), 'coreguidelines': (
    'https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#%s', '[核心准则 %s]')}

togglebutton_hint = "点击展开"
togglebutton_hint_hide = "点击隐藏"

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
    "use_sidenotes": True,
    'path_to_docs': 'docs/',
    'repository_url': 'https://github.com/FeignClaims/question_board',
    'show_nav_level': 0,
    'show_prev_next': False,
    'show_toc_level': 2,
    'use_edit_page_button': True,
    'use_issues_button': True,
    'use_source_button': True,
}
html_static_path = ['_static']
html_favicon = '_static/favicon.png'
html_search_language = 'zh'
html_last_updated_fmt = '%Y-%m-%d %H:%M:%S'
git_last_updated_timezone = 'Asia/Shanghai'
html_baseurl = 'https://question-board.readthedocs.io/'


def setup(app):
    app.add_css_file("coreguidelines.css")
    app.add_css_file("dontread.css")
    app.add_css_file("monofont.css")
    app.add_css_file("precontent.css")
    app.add_css_file("seealso.css")

    app.add_css_file("theme.css")
