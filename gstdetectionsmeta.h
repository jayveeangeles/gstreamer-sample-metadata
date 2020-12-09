#ifndef __GST_DETECTIONS_META_H__
#define __GST_DETECTIONS_META_H__

#include <gst/gst.h>
#include <gst/gstmeta.h>

G_BEGIN_DECLS
/* */
  GType gst_detectionmetas_api_get_type (void);
const GstMetaInfo *gst_detectionmetas_get_info (void);

#define GST_DETECTIONMETAS_GET(buf) ((GstDetectionMetas *)gst_buffer_get_meta(buf,gst_detectionmetas_api_get_type()))
#define GST_DETECTIONMETAS_ADD(buf) ((GstDetectionMetas *)gst_buffer_add_meta(buf,gst_detectionmetas_get_info(),(gpointer)NULL))

#define MAX_DETECTIONS 64

typedef struct
{
  gchar* label;
  gfloat confidence;
  guint xmin, ymin, xmax, ymax;

} GstObjectDetectionMeta;

typedef struct
{
  GstMeta meta;

  GstObjectDetectionMeta detections[MAX_DETECTIONS];

  guint detections_count;

} GstDetectionMetas;

GstObjectDetectionMeta* gst_detectionmetas_get_info_detections(GstBuffer*);
guint gst_detectionmetas_get_info_detections_count(GstBuffer*);

G_END_DECLS
/* */
#endif /* __GST_DETECTIONS_META_H__ */