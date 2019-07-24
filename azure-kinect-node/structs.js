const Struct = require('struct');
const CalibrationExtrinsics = Struct()
  .array('rotation', 9, 'floatle')
  .array('translation', 3, 'floatle');

const CalibrationIntrinsicParameter = Struct()
  .floatle('cx')
  .floatle('cy')
  .floatle('fx')
  .floatle('fy')
  .floatle('k1')
  .floatle('k2')
  .floatle('k3')
  .floatle('k4')
  .floatle('k5')
  .floatle('k6')
  .floatle('codx')
  .floatle('cody')
  .floatle('p2')
  .floatle('p1')
  .floatle('metric_radius')
  ;
const CalibrationIntrinsicParameters = Struct()
  .struct('param', CalibrationIntrinsicParameter)
  .array('v', 15, 'floatle');

const CalibrationIntrinsics = Struct()
  .word8('type')
  .word32Ule('parameter_count')
  .struct('parameters', CalibrationIntrinsicParameters);
const CalibrationCamera = Struct()
  .struct('extrinsics', CalibrationExtrinsics)
  .struct('intrinsics', CalibrationIntrinsics)
  .word32Ule('resolution_width')
  .word32Ule('resolution_height')
  .floatle('metric_radius');

const Calibration = Struct()
  .struct('depth_camera_calibration', CalibrationCamera)
  .struct('color_camera_calibration', CalibrationCamera)
  .array('extrinsics', 4, Struct()
    .array(0, 4, CalibrationExtrinsics)
    .array(1, 4, CalibrationExtrinsics)
    .array(2, 4, CalibrationExtrinsics)
    .array(3, 4, CalibrationExtrinsics))
  .word8('depth_mode')
  .word8('color_resolution');