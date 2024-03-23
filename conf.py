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
    'myst_parser',
    'sphinx.ext.extlinks',
    'sphinx.ext.graphviz',
    'sphinx.ext.intersphinx',
    'sphinx.ext.todo',
    'sphinx_copybutton',
    'sphinx_design',
    'sphinx_examples',
    'sphinx_last_updated_by_git',
    'sphinx_sitemap',
    'sphinx_tabs.tabs',
    'sphinx_togglebutton',
]

intersphinx_mapping = {
    "vscode_cpp_starter": ("https://vscode-cpp-starter.readthedocs.io/", "https://vscode-cpp-starter.readthedocs.io/objects.inv"),
    "change_major_exam": ("https://change-major-exam.readthedocs.io/", "https://change-major-exam.readthedocs.io/objects.inv"),
}
intersphinx_disabled_reftypes = ["*"]

extlinks = {'godbolt': ('https://godbolt.org/z/%s', '[在线代码 %s]'), 'coreguidelines': (
    'https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#%s', '[核心准则 %s]')}

togglebutton_hint = "点击展开"
togglebutton_hint_hide = "点击隐藏"

templates_path = ['_templates']
exclude_patterns = ['README.md']

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
            "name": "Gitee",
            "url": "https://gitee.com/cpp_tutorial/board",
            "icon": "fa-custom fa-gitee",
        }
    ],
    "use_sidenotes": True,
    'repository_url': 'https://github.com/FeignClaims/question_board',
    'show_nav_level': 0,
    'show_prev_next': True,
    'show_toc_level': 2,
    'use_edit_page_button': True,
    'use_issues_button': True,
    'use_source_button': True,
}
html_static_path = ['_static', '_theme']
html_favicon = '_static/favicon.png'
html_search_language = 'zh'
html_last_updated_fmt = '%Y-%m-%d %H:%M:%S'
git_last_updated_timezone = 'Asia/Shanghai'
html_baseurl = 'https://question-board.readthedocs.io/'
sitemap_filename = 'sitemapindex.xml'
sitemap_url_scheme = '{link}'
html_extra_path = [
    '_static/robots.txt',
    '_verification/b53e94a16a3cbec878b95c242d74451e.txt',
    '_verification/baidu_verify_codeva-DLE3U9izgB.html',
    '_verification/google13ac7719c05e0aea.html',
    '_verification/sogousiteverification.txt',
]


def setup(app):
    app.add_css_file("theme.css")
    app.add_js_file("gitee_icon.js")
