for %f in (*.ipynb) do @jupyter nbconvert --to script "%f"

mkdir python
move *.py python