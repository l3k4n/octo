import json, os, argparse
from jinja2 import Template

parser = argparse.ArgumentParser()
parser.add_argument("--output_dir", type=str, required=True, help="Path to the output directory")
args = parser.parse_args()
os.makedirs(args.output_dir, exist_ok=True)
properties = json.load(open("css_properties.json", "r"))

longhands = [property for property in properties if property.get("is_longhand")]
open(os.path.join(args.output_dir, "longhands.h"), "w").write(
    Template(open("templates/css_longhand_property.h.txt").read()).render({"longhands": longhands })
)

shorthands = [property for property in properties if not property.get("is_longhand")]
open(os.path.join(args.output_dir, "shorthands.h"), "w").write(
    Template(open("templates/css_shorthand_property.h.txt").read()).render({ "shorthands": shorthands })
)
