import React from 'react';
import {StyleSheet, Image, Text, TextInput, View, Button, ScrollView} from 'react-native';

type CatProps = {};
const styles = StyleSheet.create({ //约定俗成的写法

});
const FixedDimensions = (props: CatProps) => { //props:CatProps的意思是props是一个CatProps类型的对象
    return (
        <View style={{flex: 1}}>
            <View style={{flex: 1, backgroundColor: 'powderblue'}} />
            <View style={{flex: 2, backgroundColor: 'skyblue'}} />
            <View style={{flex: 3, backgroundColor: 'steelblue'}} />
        </View>
    );
};

export default FixedDimensions;