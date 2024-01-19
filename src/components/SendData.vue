<template>
    <div>
      <form @submit.prevent="submitData">
        <label for="dataInput">Data:</label>
        <input v-model="data" type="text" id="dataInput" />
        <button type="submit">Submit</button>
      </form>
  
      <!-- Button to send the number 1 -->
      <button @click="sendNumber">Send Number 1</button>
    </div>
  </template>
  
  <script>
  import { db, set, ref } from '@/components/firebase'; // Adjust the path accordingly
  
  export default {
    data() {
      return {
        data: '',
      };
    },
    methods: {
      submitData() {
        // Replace everything at the specified path 'your_data_path'
        set(ref(db, 'servo'), {
          data: this.data,
        });
  
        // Clear the input field after submission
        this.data = '';
      },
      sendNumber() {
        // Replace everything at the specified path 'your_data_path'
        set(ref(db, 'motor'), {
          data: 1,
        });
      },
    },
  };
  </script>
  