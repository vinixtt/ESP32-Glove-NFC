// IMPORTS - Bringing tools we'll use
import React, { useState } from 'react';  // useState = store data that changes
import {
  SafeAreaView,    // Safe area (avoids phone notch)
  View,            // Container (like a div in HTML)
  Text,            // Text
  TouchableOpacity, // Clickable button
  StyleSheet,      // Styles (like CSS)
  StatusBar,       // Phone status bar
} from 'react-native';

// MAIN COMPONENT - Every React app has components
// Component = Reusable UI block
function App(): React.JSX.Element {
  
  // STATE - Data that CHANGES during app usage
  // Format: [value, functionToChange] = useState(initialValue)
  const [isConnected, setIsConnected] = useState(false);  // Connected? false at start
  const [deviceName, setDeviceName] = useState('');       // Device name
  const [nfcData, setNfcData] = useState('');             // NFC data received

  // FUNCTION - Connect to ESP32 via Bluetooth
  const connectToDevice = () => {
    // For now, just simulates connection
    // Later we'll implement real BLE!
    setIsConnected(true);
    setDeviceName('ESP32-NFC');
    console.log('Trying to connect...');
  };

  // FUNCTION - Disconnect
  const disconnectDevice = () => {
    setIsConnected(false);
    setDeviceName('');
    setNfcData('');
    console.log('Disconnected');
  };

  // RENDER - What appears on screen
  // JSX = HTML + JavaScript together
  return (
    <SafeAreaView style={styles.container}>
      <StatusBar barStyle="light-content" backgroundColor="#1a1a2e" />
      
      {/* Header */}
      <View style={styles.header}>
        <Text style={styles.title}>NFC Reader</Text>
        <Text style={styles.subtitle}>ESP32 Bluetooth Connection</Text>
      </View>

      {/* Status Card */}
      <View style={styles.statusCard}>
        <Text style={styles.statusLabel}>Status:</Text>
        <Text style={[
          styles.statusText,
          isConnected ? styles.connected : styles.disconnected
        ]}>
          {isConnected ? 'Connected' : 'Disconnected'}
        </Text>
        
        {isConnected && deviceName && (
          <Text style={styles.deviceName}>Device: {deviceName}</Text>
        )}
      </View>

      {/* NFC Data Display */}
      {isConnected && (
        <View style={styles.dataCard}>
          <Text style={styles.dataLabel}>NFC Data:</Text>
          <Text style={styles.dataText}>
            {nfcData || 'Waiting for tag...'}
          </Text>
        </View>
      )}

      {/* Connect/Disconnect Button */}
      <TouchableOpacity
        style={[
          styles.button,
          isConnected ? styles.buttonDisconnect : styles.buttonConnect
        ]}
        onPress={isConnected ? disconnectDevice : connectToDevice}
      >
        <Text style={styles.buttonText}>
          {isConnected ? 'Disconnect' : 'Connect to ESP32'}
        </Text>
      </TouchableOpacity>

      {/* Info Footer */}
      <View style={styles.footer}>
        <Text style={styles.footerText}>
          {isConnected 
            ? 'Ready to scan NFC tags' 
            : 'Tap button to connect'}
        </Text>
      </View>
    </SafeAreaView>
  );
}

// STYLES - React Native CSS
// Uses camelCase: background-color becomes backgroundColor
const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#1a1a2e',
    padding: 20,
  },
  header: {
    alignItems: 'center',
    marginTop: 20,
    marginBottom: 40,
  },
  title: {
    fontSize: 32,
    fontWeight: 'bold',
    color: '#ffffff',
    marginBottom: 8,
  },
  subtitle: {
    fontSize: 16,
    color: '#a0a0a0',
  },
  statusCard: {
    backgroundColor: '#16213e',
    borderRadius: 12,
    padding: 20,
    marginBottom: 20,
    borderWidth: 1,
    borderColor: '#0f3460',
  },
  statusLabel: {
    fontSize: 14,
    color: '#a0a0a0',
    marginBottom: 8,
  },
  statusText: {
    fontSize: 20,
    fontWeight: 'bold',
  },
  connected: {
    color: '#4ecca3',
  },
  disconnected: {
    color: '#e94560',
  },
  deviceName: {
    fontSize: 14,
    color: '#a0a0a0',
    marginTop: 8,
  },
  dataCard: {
    backgroundColor: '#16213e',
    borderRadius: 12,
    padding: 20,
    marginBottom: 20,
    borderWidth: 1,
    borderColor: '#0f3460',
    minHeight: 100,
  },
  dataLabel: {
    fontSize: 14,
    color: '#a0a0a0',
    marginBottom: 8,
  },
  dataText: {
    fontSize: 18,
    color: '#ffffff',
    fontFamily: 'monospace',
  },
  button: {
    borderRadius: 12,
    padding: 18,
    alignItems: 'center',
    marginTop: 'auto',
    marginBottom: 20,
  },
  buttonConnect: {
    backgroundColor: '#4ecca3',
  },
  buttonDisconnect: {
    backgroundColor: '#e94560',
  },
  buttonText: {
    fontSize: 18,
    fontWeight: 'bold',
    color: '#ffffff',
  },
  footer: {
    alignItems: 'center',
    paddingBottom: 20,
  },
  footerText: {
    fontSize: 14,
    color: '#a0a0a0',
    fontStyle: 'italic',
  },
});

export default App;