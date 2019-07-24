{
    "targets": [
        {
            "target_name": "azure_kinect",
            "sources": [
                "cpp/addon.cc",
                "cpp/azure-kinect.cc",
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
            ],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
            "conditions": [
                ['OS=="win"', {
                    'include_dirs': [
                        "<(module_root_dir)/include"
                    ],
                    "libraries": [
                        "<(module_root_dir)/lib/win/k4a.lib",
                        "<(module_root_dir)/lib/win/k4arecord.lib",
                        "<(module_root_dir)/lib/win/k4abt.lib",
                    ],
                     "copies": [
                        {
                            "destination": "<(module_root_dir)/build/Release",
                            "files": [
                                "<(module_root_dir)/lib/win/k4a.dll",
                                "<(module_root_dir)/lib/win/k4arecord.dll",
                                "<(module_root_dir)/lib/win/k4abt.dll",
                            ]
                        }   
                    ],
                }],
            ],
        },
    ],
}
