#ifndef __GST_TRACKED_META_H__
#define __GST_TRACKED_META_H__

#include <gst/gst.h>
#include <gst/gstmeta.h>

G_BEGIN_DECLS
/* */
  GType gst_trackedmetas_api_get_type (void);
const GstMetaInfo *gst_trackedmetas_get_info (void);

#define GST_TRACKEDMETAS_GET(buf) ((GstTrackedMetas *)gst_buffer_get_meta(buf,gst_trackedmetas_api_get_type()))
#define GST_TRACKEDMETAS_ADD(buf) ((GstTrackedMetas *)gst_buffer_add_meta(buf,gst_trackedmetas_get_info(),(gpointer)NULL))

#define MAX_TRACKED 64

typedef struct
{
  gchar* id;
  gchar* label;
  gfloat confidence;
  guint xmin, ymin, xmax, ymax;

} GstTrackedMeta;

typedef struct
{
  GstMeta meta;

  GstTrackedMeta tracked[MAX_TRACKED];

  guint tracked_count;

} GstTrackedMetas;

GstTrackedMeta* gst_trackedmetas_get_info_tracked(GstBuffer*);
guint gst_trackedmetas_get_info_tracked_count(GstBuffer*);

G_END_DECLS
/* */
#endif /* __GST_TRACKED_META_H__ */