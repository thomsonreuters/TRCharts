/*******************************************************************************
 * Copyright 2015 Thomson Reuters
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

package com.thomsonreuters.corptech.tr3dutils;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.support.v4.util.LruCache;
import android.text.TextPaint;
import android.util.Log;

public final class TRChartsTextRenderer {
    private static final String LOG_TAG = "TR3DUtils";

    private static final LruCache<String, Typeface> TYPEFACE_LRU_CACHE = new LruCache<String, Typeface>(
            5);

    private static final Rect RECT_AUX = new Rect();

    private static final TextPaint PAINT_AUX = new TextPaint();

    private static AssetManager sAssetManager;

    private static Canvas sCanvasAux = new Canvas();

    private static boolean isInit = false;

    public static void initialize(final AssetManager mAssetManager) {
        TRChartsTextRenderer.sAssetManager = mAssetManager;
        if (!isInit) {
            sCanvasAux.scale(1, -1);
            isInit = true;
        }
    }

    private static boolean assertInit() {
        return null == sAssetManager || !isInit;
    }

    public static long generateAndUploadTexture(final String text, final String fontName,
            final long fontSize, final long texID) {
        if (assertInit()) {
            Log.e(LOG_TAG, "TextRenderer not initialized");
            return 0;
        }
        if(!GLES20.glIsTexture((int) texID)){
            Log.e(LOG_TAG, "TexId received is not a GlTexture");
            return 0;
        }
        Typeface face = (fontName.equals("DEFAULT") || fontName.isEmpty()) ? Typeface.DEFAULT
                : TYPEFACE_LRU_CACHE.get(fontName);
        if (face == null) {
            try {
                face = Typeface.createFromAsset(sAssetManager, fontName);
            } catch (final Exception fontError) {
                Log.e(LOG_TAG, "Failed to load font", fontError);
                return 0;
            }
            TYPEFACE_LRU_CACHE.put(fontName, face);
        }
        PAINT_AUX.setTypeface(face);
        PAINT_AUX.setTextSize(fontSize);
        final String lines[] = text.split("\n");
        int textWidth = 0;
        final int layouts[] = new int[lines.length];
        int textHeight = 0;
        int i = 0;
        int bottom = 0;
        final int left[] = new int[lines.length];
        for (final String line : lines) {
            PAINT_AUX.getTextBounds(line, 0, line.length(), RECT_AUX);
            textWidth = Math.max(textWidth, RECT_AUX.width());
            layouts[i] = RECT_AUX.height();
            textHeight += layouts[i];
            bottom = RECT_AUX.bottom;
            left[i] = RECT_AUX.left;
            i++;
        }
        if (textWidth == 0 || textHeight == 0){
            Log.e(LOG_TAG, "Received text request where a dimension is 0");
            return 0;
        }
        // TODO check if text size is bigger than allowed texture size
        // causes: font too big + text too long as no max line length
        final Bitmap bitmapAux = Bitmap
                .createBitmap(textWidth, textHeight, Bitmap.Config.ARGB_8888);
        sCanvasAux.setBitmap(bitmapAux);
        int offset = -bottom;
        for (i = lines.length - 1; i >= 0; i--) {
            sCanvasAux.drawText(lines[i], -left[i], offset, PAINT_AUX);
            offset -= layouts[i];
        }
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, (int)texID);
        GLES20.glPixelStorei(GLES20.GL_UNPACK_ALIGNMENT, 1);
        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmapAux, 0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
        final long mask = (bitmapAux.getWidth() << 16) | bitmapAux.getHeight();
        return mask;
    }
}
