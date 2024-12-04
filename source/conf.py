# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Embedded Tutorials'
copyright = '2024, Sagar Chaudhary'
author = 'Sagar Chaudhary'
release = '1.0.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'sphinx_copybutton',
    'myst_parser',
    'sphinx.ext.linkcode',
    'sphinx.ext.mathjax',
]

templates_path = ['_templates']
exclude_patterns = []

language = 'en'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

html_context = {
    "display_github": True,
    "github_user": "sagar-bei031",
    "github_repo": "EmbeddedTutorials",
    "github_version": "main",
    "conf_py_path": "/source/",
}

source_suffix = {
    '.rst': 'restructuredtext',
    '.txt': 'markdown',
    '.md': 'markdown',
}


def linkcode_resolve(domain, info):
    """
    Determine the URL corresponding to Python object.
    """
    if domain != "py":
        return None
    if not info["module"]:
        return None

    filename = info["module"].replace(".", "/")
    return f"https://github.com/sagar-bei031/EmbeddedDocumentation/blob/main/{filename}.py"
