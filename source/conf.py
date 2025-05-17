# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Embedded Tutorials'
copyright = '2024 - 2025, Robotics Club, Pulchowk Campus'
author = 'Sagar Chaudhary'
release = '1.1.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'sphinx_copybutton',
    'myst_parser',
    'sphinx.ext.linkcode',
    'sphinx.ext.mathjax',
    'sphinx.ext.extlinks',
    'sphinx_tabs.tabs',
]

templates_path = ['_templates']
exclude_patterns = [
     'intermediate_tutorial/files/**',  # Exclude all files in this directory
]

language = 'en'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
html_logo = "_static/club-logo.svg"

html_context = {
    "display_github": True,
    "github_user": "Robotics-Club-Pulchowk",
    "github_repo": "EmbeddedTutorials",
    "github_version": "main",
    "conf_py_path": "/source/",
}

html_css_files = [
    'custom.css',
]

html_js_files = [
    'custom.js',
]

source_suffix = {
    '.rst': 'restructuredtext',
    '.txt': 'markdown',
    '.md': 'markdown',
}

issues_github_path = "sagar-bei031/EmbeddedTutorials"

# -- Options for linkcode extension ------------------------------------------
def linkcode_resolve(domain, info):
    """
    Determine the URL corresponding to Python object.
    """
    if domain != "py":
        return None
    if not info["module"]:
        return None

    filename = info["module"].replace(".", "/")
    return f"https://github.com/Robotics-Club-Pulchowk/EmbeddedDocumentation/blob/main/{filename}.py"

extlinks = {
    'newtab': ('%s', '')
}

sphinx_tabs_disable_tab_closing = True