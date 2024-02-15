<template>
  <div id="app">
    <SendData />
    <GridComponent/>
  </div>
</template>

<script>
import SendData from './components/SendData.vue'
import GridComponent from './components/GridComponent.vue'

export default {
  name: 'App',
  components: {
    SendData,
    GridComponent
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: #e0e0e0; /* Lighter text for readability */
  background-color: #121212; /* Dark background */
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  padding: 60px 0;
}

.content {
  max-width: 600px;
  margin: auto;
  padding: 20px;
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.5); /* Stronger shadow for depth */
  border-radius: 10px;
  background-color: #222; /* Slightly lighter dark shade for content background */
}
</style>

