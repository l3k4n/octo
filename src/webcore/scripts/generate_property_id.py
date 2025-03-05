import json, os, argparse
from jinja2 import Template

parser = argparse.ArgumentParser()
parser.add_argument("--output_dir", type=str, required=True, help="Path to the output directory")
parser.add_argument("--properties_file", type=argparse.FileType('r'), required=True, help="Path to the properties json file")
args = parser.parse_args()
os.makedirs(args.output_dir, exist_ok=True)
properties = json.load(args.properties_file)

open(os.path.join(args.output_dir, "propertyid.h"), "w").write(
    Template(open("templates/css_property_id.h.txt").read()).render({ "properties": properties })
)
