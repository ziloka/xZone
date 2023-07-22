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

run generate graph script
```
poetry run python src/generate.py
```