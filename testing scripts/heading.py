
import getopt
import re
import sys
from pathlib import Path

PATTERN = re.compile(
    r"/\*.*program name:.*?\s.*?author:.*\s.*?date last updated:\s*(1[12]|0?[1-9])\/((1|2)[0-9]|0?[1-9]|3[01])\/(20)?2[6789]\s.*?purpose:",
    re.DOTALL | re.IGNORECASE,
)

def search_file(filename : str) -> list[str]:
    path = Path(filename)
    if not path.exists():
        print(f"{filename}: file not found")
        return []
    text = path.read_text(encoding="utf-8", errors="ignore")
    return PATTERN.findall(text) if PATTERN.search(text) else []

def main() -> None:
    args = sys.argv[1:]
    options = "f:"
    long_options = ["File="]
    
    try:
        arguments, values = getopt.getopt(args, options, long_options)
        for currentArg, currentVal in arguments:
            if currentArg in("-f", "--File"):
                result = search_file(currentVal)
                found = False
                for match in result:
                    found = True
                    print(f"{currentVal}: match:")
                    print(match.group(0))
                    print("-" * 40)
                if not found:
                    print(f"{currentVal}: no match found")
    except getopt.error as err:
        print(str(err))



if __name__ == "__main__":
    main() 
