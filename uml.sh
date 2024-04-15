# Include all .hpp files in the hpp2plantuml binary

if ! command -v hpp2plantuml &> /dev/null
then
    echo "hpp2plantuml could not be found"
    echo "install with \"pip install hpp2plantuml\""
    exit 1
fi


find src/ -name "*.hpp" -exec echo -i {} \; | xargs hpp2plantuml -o assets/plantuml/plantuml.puml
