### Generate graph

Installation
- install poetry 
Unix 
```sh
curl -sSL https://install.python-poetry.org | python3 -
```

Windows
```pwsh
(Invoke-WebRequest -Uri https://install.python-poetry.org -UseBasicParsing).Content | py -
```

Program was last ran using python 3.11.6

run generate graph script
```
python -m venv .
poetry install
poetry run python src/generate.py
```