import React, {useState} from 'react';
import {StyleSheet, Image, Text, TextInput, View, Button, ScrollView} from 'react-native';

type CatProps = {};
const styles = StyleSheet.create({ //约定俗成的写法
    scroll_view_container: {
        backgroundColor: 'white',
    },
    container: {
        marginTop: 50,
        flex: 1,
    },
    red: {
        color: 'red',
    },
    text_container: {
        justifyContent: 'center',
    }
});
const Cat = (props: CatProps) => { //props:CatProps的意思是props是一个CatProps类型的对象
    let [isHungry, setIsHungry] = useState(0); //useState(true)的意思是isHungry的初始值是true
    let name = ''
    return (
        <View style={{flexDirection: 'column'}}>
            <ScrollView style={styles.scroll_view_container}>
                <Text></Text>
                {/*//换行*/}
                <Text style={styles.red}>FEED {isHungry}</Text>
                <Text id="pet">
                    I am {name}, and I am {
                    isHungry === 0 ? 'hungry' : isHungry === 1 ? 'full' : 'very full'}!
                </Text>
                <Button
                    onPress={() => {
                        setIsHungry(isHungry + 1);
                    }}
                    disabled={isHungry === 2} //disabled是button的一个属性，当isHungry为false时，button不可点击
                    title={isHungry === 0 ? 'FEED ME' : isHungry === 1 ? 'THANKS' : 'TOO MUCH'} //这里必须用三元运算符，不能用if else，因为这是jsx语法
                />
                <Button
                    title="RESET"
                    onPress={() => {
                        setIsHungry(0);

                    }}
                    disabled={isHungry === 0}
                    //将按钮设置为红色
                    color="red"
                />
                <View style={{alignItems: 'center', justifyContent: 'center'}}>
                    <Image
                        source={{
                            uri: 'https://reactnative.dev/docs/assets/p_cat2.png',
                        }}
                        style={{width: 200, height: 200, justifyContent: 'center'}}
                    />
                </View>
            </ScrollView>
            <View style={styles.text_container}>
                <TextInput
                    //TextInput输入框有两个回调函数，一个是onChangeText，一个是onSubmitEditing
                    placeholder={'Name me!'}
                    style={{
                        height: 40,
                        borderColor: 'gray',
                        borderWidth: 1,
                    }}
                    onChangeText={(text) => {
                        name = text;
                    }}
                />
            </View>
        </View>

    );
};

export default Cat;