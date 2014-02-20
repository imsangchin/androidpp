//
//  CharacterStyle.h
//  Androidpp
//
//  Created by Saul Howard on 1/22/14.
//  Copyright (c) 2014 MoneyDesktop. All rights reserved.
//

#ifndef __Androidpp__CharacterStyle__
#define __Androidpp__CharacterStyle__

#include "AndroidMacros.h"

#include "Android/utils/Object.h"

#include <string>
#include <memory>

using namespace std;

ANDROID_BEGIN

class TextPaint;

/**
 * The classes that affect character-level text formatting extend this
 * class.  Most extend its subclass {@link MetricAffectingSpan}, but simple
 * ones may just implement {@link UpdateAppearance}.
 */
class CharacterStyle : public Object {
    
public:
    
    virtual void updateDrawState(shared_ptr<TextPaint> tp) = 0;
    
    /**
     * A given CharacterStyle can only applied to a single region of a given
     * Spanned.  If you need to attach the same CharacterStyle to multiple
     * regions, you can use this method to wrap it with a new object that
     * will have the same effect but be a distinct object so that it can
     * also be attached without conflict.
     */
    static shared_ptr<CharacterStyle> wrap(shared_ptr<CharacterStyle> cs);
    
    /**
     * Returns "this" for most CharacterStyles, but for CharacterStyles
     * that were generated by {@link #wrap}, returns the underlying
     * CharacterStyle.
     */
    virtual CharacterStyle *getUnderlying() {
        return this;
    }
    
    virtual string getType() {
        return "CharacterStyle";
    };
    
    /**
     * A Passthrough CharacterStyle is one that
     * passes {@link #updateDrawState} calls through to the
     * specified CharacterStyle while still being a distinct object,
     * and is therefore able to be attached to the same Spannable
     * to which the specified CharacterStyle is already attached.
     */
    class Passthrough;
};

class CharacterStyle::Passthrough : public CharacterStyle {

private:
    
    shared_ptr<CharacterStyle> mStyle;
    
public:
    
    /**
     * Creates a new Passthrough of the specfied CharacterStyle.
     */
    Passthrough(shared_ptr<CharacterStyle> cs) {
        mStyle = cs;
    }
    
    /**
     * Passes updateDrawState through to the underlying CharacterStyle.
     */
    void updateDrawState(shared_ptr<TextPaint> tp) {
        mStyle->updateDrawState(tp);
    }
    
    /**
     * Returns the CharacterStyle underlying this one, or the one
     * underlying it if it too is a Passthrough.
     */
    CharacterStyle *getUnderlying() {
        return mStyle->getUnderlying();
    }
};

ANDROID_END

#endif /* defined(__Androidpp__CharacterStyle__) */