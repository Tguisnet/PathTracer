#!/usr/bin/env python3

import json
import sys

# For now, fog is discarded

json_mtl_vec_bindings = {
        'diffuse': 'Kd',
        'specular': 'Ks',
}

json_mtl_num_bindings = {
        'spec-level': 'Ns',
        'shininess': 'illum',
        'opacity': 'd',
        'refr-index': 'Ni',
}

json_mtl_num_to_vec_bindings = {
        'reflectivity': 'Ka',
}

def print_mtl(material):
    for key, binding in json_mtl_num_bindings.items():
        print(binding, material[key])

    for key, binding in json_mtl_vec_bindings.items():
        vec = material[key]
        print(binding, vec[0], vec[1], vec[2])

    for key, binding in json_mtl_num_to_vec_bindings.items():
        vec = [material[key]] * 3
        print(binding, vec[0], vec[1], vec[2])

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage:', sys.argv[0], '<JSON text>', file=sys.stderr)
        exit(1)

    data = sys.argv[1]

    try:
        material = json.loads(data)
        print_mtl(material)
    except json.JSONDecodeError as err:
        print('Error on JSON parsing:', err);
