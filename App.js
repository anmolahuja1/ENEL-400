import { StatusBar } from 'expo-status-bar';
import React, { useState } from 'react';
import { StyleSheet, Text, View, Button } from 'react-native';

export default function App() {
  const [outputText, setOutputText] = useState('Open up App.js to start working on your app!');
  return (
    <View style={styles.container}>
      <StatusBar style="auto"></StatusBar>
      <Text>{outputText}</Text>
      <Text style={styles.title}>The SmartBox</Text>

      <View style={{margin:10, padding:20}}>
        <Button title="Button 1" onPress={() => setOutputText('hey')}/>
      </View>

      <View style={{margin:10, padding:20}}>
        <Button title="Button 2" onPress={() => setOutputText('hi')}/>
      </View>

      <View style={{margin:10, padding:20}}>
        <Button title="Button 3" onPress={() => setOutputText('hello')}/>
      </View>

    </View>

  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 24,
    backgroundColor: '#fff',
    alignItems: 'center',
    marginTop: 60,
    padding: 30
  },

  title:{
    marginTop: 16,
    paddingVertical: 8,
    borderWidth: 4,
    borderColor: "#20232a",
    borderRadius: 6,
    backgroundColor: "#61dafb",
    color: "#20232a",
    textAlign: "center",
    fontSize: 30
  },

});

