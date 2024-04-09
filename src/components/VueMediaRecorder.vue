<template>
    <div class="container">
      <video v-if="stream" :srcObject.prop="stream" autoplay playsinline class="webcam"></video>
      <div v-if="error" class="error">{{ error }}</div>
      <button v-if="!isRecording" @click="startRecording">Start Camera</button>
      <button v-if="isRecording" @click="stopRecording">Stop Camera</button>
    </div>
  </template>
  
  <script>
  import { useMediaRecorder } from 'vue-media-recorder';
  
  export default {
    setup() {
      const { stream, error, start, stop, isRecording } = useMediaRecorder({ audio: false, video: true });
  
      function startRecording() {
        start();
      }
  
      function stopRecording() {
        stop();
      }
  
      return {
        stream,
        error,
        startRecording,
        stopRecording,
        isRecording
      };
    }
  };
  </script>
  
  <style>
  .container {
    display: flex;
    flex-direction: column;
    align-items: center;
    margin-top: 20px;
  }
  
  .webcam {
    width: 80%; /* Adjust width as needed to fit the layout */
    border: 3px solid #666;
  }
  
  .error {
    color: red;
    margin: 20px;
  }
  
  button {
    margin: 10px;
    padding: 10px 20px;
    font-size: 16px;
    cursor: pointer;
  }
  </style>
  