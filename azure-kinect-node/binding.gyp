{
    "targets": [
        {
            "target_name": "hello",
            "sources": ["hello.cc"],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "/Source/gigi/azure-kinect-node/include"
            ],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "libraries": [
                "/Source/gigi/azure-kinect-node/lib/k4a.lib"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        }
    ]
}
