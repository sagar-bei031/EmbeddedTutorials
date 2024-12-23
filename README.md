# EmbeddedTutorials

**EmbeddedTutorials** web pages are hosted [here](https://Robotics-Club-Pulchowk.github.io/EmbeddedTutorials/).


## Build

```bash
# Create Virtual Environment
python3 -m venv venv
source ./venv/bin/acivate

# Install sphinx package and extensions
pip3 install sphinx sphinx_rtd_theme myst-parser sphinx-copybutton sphinx_new_tab_link

# Build html
make html

# Run Webpages
cd build/html
python3 -m http.server # OR, firefox index.html
```
