import {StatusBar} from 'expo-status-bar';
import {StyleSheet, Text, View, TextInput, ScrollView, Image} from 'react-native';
import ChatView from "./component/ChatView";
import TextBar from "./component/TextBar";

export default function App() {
    return (
        //View标签应该占据整个空间
        <View style={{flex: 1}}>
            <View style={{flex: 3, backgroundColor: 'powderblue'}}>
                <ChatView>


                </ChatView>
            </View>
            <View style={{flex: 1, backgroundColor: 'skyblue'}}>
                <TextBar>

                </TextBar>
            </View>
        </View>
    );
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#fff',
        alignItems: 'center',
        justifyContent: 'center',
    },
});
