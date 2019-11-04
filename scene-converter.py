#!/usr/bin/env python3

'''
Converts Tungsten scenes to our format

Please acknowledge that this converter is not
complete and will probably not provide a working
scene for our pathtracer
'''

import json
import sys

def minus3(lhs, rhs):
    return [lhs[i] - rhs[i] for i in range(3)]

def expand3(v):
    return [v] * 3 if not isinstance(v, list) else v

scene_input = json.loads(sys.stdin.read())

camera = scene_input['camera']
camera_tr = camera['transform']
primitives = scene_input['primitives']
bsdfs = scene_input['bsdfs']

meshes_set = set(prim['file'] for prim in primitives if 'file' in prim)
meshes = dict(reversed(enum) for enum in enumerate(meshes_set))

scene_output = {
        'width': camera['resolution'][0] if type(camera['resolution']) is list else camera['resolution'],
        'height': camera['resolution'][1] if type(camera['resolution']) is list else camera['resolution']
}

scene_output['camera'] = {
        'pos': camera_tr['position'],
        'forward': minus3(camera_tr['look_at'], camera_tr['position']),
        'up': camera_tr['up'],
        'fov': camera['fov']
}

scene_output['meshes'] = [mesh.replace('.wo3', '.obj') for mesh in meshes_set]

scene_output['materials'] = [
        {
            'type': bsdf['type'],
            'albedo': expand3(bsdf['albedo'])
        }
        for bsdf in bsdfs
]

materials = dict(reversed(enum) for enum in enumerate(bsdf['name'] for bsdf in bsdfs))

scene_output['objects'] = [
        {**{
            'mesh': meshes[prim['file']] if 'file' in prim else -1,
            'mtl': materials[prim['bsdf']] if 'bsdf' in prim else -1,
            'position': [0] * 3,
            'scale': [1] * 3,
            'rotation': [0] * 3,
            'emissive': expand3(prim['power']) if 'power' in prim else [0] * 3,
        }, **prim.get('transform', [])}
        for prim in primitives
]

print(json.dumps(scene_output, indent=4))
